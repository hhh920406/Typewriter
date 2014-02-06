#include <QToolBar>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetItem>
#include "ColorWidget.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initToolBar();
    this->setWindowState(Qt::WindowMaximized);
    this->_clientManager.load();
    this->updateTableWidget();

    this->_tcpServer = new TcpServer(&this->_clientManager);
    this->_tcpServer->listen(19627);
    this->connect(this->_tcpServer, SIGNAL(newClient(qint32)), this, SLOT(newClient(qint32)));

    this->_udpServer = new UdpServer(&this->_clientManager);
    this->_udpServer->listen(19627);
    this->connect(this->_udpServer, SIGNAL(updateClient(qint32)), this, SLOT(updateClient(qint32)));
    this->connect(this->_udpServer, SIGNAL(closeClient(qint32)), this, SLOT(closeClient(qint32)));

    this->_summarySubWindow = new LineChartWidget(this);
    this->_summarySubWindow->setWindowTitle(tr("RTT Summary"));
    this->_summarySubWindow->setClientManager(&this->_clientManager);
    this->ui->mdiArea->addSubWindow(this->_summarySubWindow)->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->_tcpServer;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    this->_clientManager.save();
}

void MainWindow::initToolBar()
{
    this->ui->mainToolBar->addAction(this->ui->actionStart_S);
    this->ui->mainToolBar->addAction(this->ui->actionPause_P);
    this->ui->mainToolBar->addAction(this->ui->actionStop_E);
    this->ui->mainToolBar->addSeparator();
    this->ui->mainToolBar->addAction(this->ui->actionCascade);
    this->ui->mainToolBar->addAction(this->ui->actionTile);
    this->ui->mainToolBar->addSeparator();
    this->ui->mainToolBar->addAction(this->ui->actionOption_O);
}

void MainWindow::updateTableRow(const qint32 row, ClientInfo *client)
{
    QCheckBox *checkBox;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QTableWidgetItem *tableWidgetItem;
    tableWidgetItem = new QTableWidgetItem(QString("%1").arg(client->magic()));
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignCenter);
    this->ui->tableWidget->setItem(row, 0, tableWidgetItem);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(client->show());
    this->connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(showChanged(bool)));
    this->ui->tableWidget->setCellWidget(row, 1, checkBox);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(client->alert());
    this->connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(alertChanged(bool)));
    this->ui->tableWidget->setCellWidget(row, 2, checkBox);
    ColorWidget *colorWidget = new ColorWidget(this);
    colorWidget->setColor(client->color());
    this->connect(colorWidget, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
    this->ui->tableWidget->setCellWidget(row, 3, colorWidget);
    tableWidgetItem = new QTableWidgetItem();
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignCenter);
    switch (client->status())
    {
    case ClientInfo::STATUS_STOPPED:
        tableWidgetItem->setText(tr("STOPPED"));
        break;
    case ClientInfo::STATUS_MONITORING:
        tableWidgetItem->setText(tr("MONITOR"));
        break;
    case ClientInfo::STATUS_SUSPENDING:
        tableWidgetItem->setText(tr("SUSPEND"));
        break;
    }
    this->ui->tableWidget->setItem(row, 4, tableWidgetItem);
    tableWidgetItem = new QTableWidgetItem(client->name());
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->ui->tableWidget->setItem(row, 5, tableWidgetItem);
    tableWidgetItem = new QTableWidgetItem(client->clientAddr().ip());
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->ui->tableWidget->setItem(row, 6, tableWidgetItem);
    tableWidgetItem = new QTableWidgetItem(client->detectAddr());
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->ui->tableWidget->setItem(row, 7, tableWidgetItem);
    spinBox = new QSpinBox(this);
    spinBox->setMaximum(10000000);
    spinBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    spinBox->setSuffix(" ms");
    spinBox->setValue(client->alertThreshold());
    this->connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(editAlert(int)));
    this->ui->tableWidget->setCellWidget(row, 8, spinBox);
    tableWidgetItem = new QTableWidgetItem(client->lastActivity());
    tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    tableWidgetItem->setTextAlignment(Qt::AlignCenter);
    this->ui->tableWidget->setItem(row, 9, tableWidgetItem);
    pushButton = new QPushButton(tr("Delete"), this);
    this->connect(pushButton, SIGNAL(clicked()), this, SLOT(deleteClient()));
    this->ui->tableWidget->setCellWidget(row, 10, pushButton);
    this->ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::updateTableMagic(const qint32 magic)
{
    for (qint32 i = 0; i < this->ui->tableWidget->rowCount(); ++i)
    {
        if (this->ui->tableWidget->item(i, 0)->text().toInt() == magic)
        {
            this->updateTableRow(i, this->_clientManager.client(magic));
            break;
        }
    }
}

void MainWindow::updateTableWidget()
{
    QVector<ClientInfo> *clients = this->_clientManager.clients();
    while (this->ui->tableWidget->rowCount())
    {
        this->ui->tableWidget->removeRow(0);
    }
    for (qint32 i = 0; i < clients->size(); ++i)
    {
        this->ui->tableWidget->insertRow(0);
        this->updateTableRow(0, &(*clients)[i]);
    }
}

void MainWindow::updateSubWindowMagic(const qint32 magic)
{
    if (this->_subWindows.find(magic) == this->_subWindows.end())
    {
        if (this->_clientManager.client(magic)->show())
        {
            LineChartWidget *widget = new LineChartWidget(this);
            widget->setClientManager(&this->_clientManager);
            widget->setUseMagic(true);
            widget->setMagic(magic);
            widget->setWindowTitle(this->_clientManager.client(magic)->name());
            this->_subWindows[magic] = this->ui->mdiArea->addSubWindow(widget);
            this->_subWindows[magic]->show();
        }
    }
    else
    {
        if (this->_clientManager.client(magic)->show())
        {
            this->_subWindows[magic]->update();
        }
        else
        {
            removeSubWindowMagic(magic);
        }
    }
}

void MainWindow::removeSubWindowMagic(const qint32 magic)
{
    if (this->_subWindows.find(magic) != this->_subWindows.end())
    {
        this->_subWindows[magic]->hide();
        this->ui->mdiArea->removeSubWindow(this->_subWindows[magic]);
        this->_subWindows.remove(magic);
    }
}

void MainWindow::newClient(qint32 magic)
{
    ClientInfo *client = this->_clientManager.client(magic);
    for (qint32 i = 0; i < this->ui->tableWidget->rowCount(); ++i)
    {
        if (this->ui->tableWidget->item(i, 0)->text().toInt() == magic)
        {
            this->ui->tableWidget->item(i, 4)->setText("MONITOR");
            this->_summarySubWindow->update();
            this->updateSubWindowMagic(magic);
            return;
        }
    }
    this->ui->tableWidget->insertRow(0);
    this->updateTableRow(0, client);
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::updateClient(qint32 magic)
{
    for (qint32 i = 0; i < this->ui->tableWidget->rowCount(); ++i)
    {
        if (this->ui->tableWidget->item(i, 0)->text().toInt() == magic)
        {
            this->ui->tableWidget->item(i, 4)->setText("MONITOR");
            this->ui->tableWidget->item(i, 9)->setText(this->_clientManager.client(magic)->lastActivity());
            if (this->_clientManager.client(magic)->alert())
            {
                if (this->_clientManager.client(magic)->rtts()->last() > this->_clientManager.client(magic)->alertThreshold())
                {
                    this->_clientManager.client(magic)->setAlert(false);
                    QMessageBox::critical(this, "RTT", QString("The RTT of %1 exceed the threshold. ").arg(this->_clientManager.client(magic)->name()));
                }
            }
            break;
        }
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::closeClient(qint32 magic)
{
    for (qint32 i = 0; i < this->ui->tableWidget->rowCount(); ++i)
    {
        if (this->ui->tableWidget->item(i, 0)->text().toInt() == magic)
        {
            this->ui->tableWidget->item(i, 4)->setText("STOPPED");
            break;
        }
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::deleteClient()
{
    QPushButton *pushButton = qobject_cast<QPushButton*>(sender());
    if (0L == pushButton)
    {
        return;
    }
    qint32 rowIndex = this->ui->tableWidget->indexAt(QPoint(pushButton->frameGeometry().x(), pushButton->frameGeometry().y())).row();
    qint32 magic = this->ui->tableWidget->item(rowIndex, 0)->text().toInt();
    ClientInfo *client = this->_clientManager.client(magic);
    if (0L != client)
    {
        this->_clientManager.removeClient(*client);
        this->ui->tableWidget->removeRow(rowIndex);
    }
    this->_summarySubWindow->update();
    this->removeSubWindowMagic(magic);
}

void MainWindow::showChanged(bool value)
{
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(sender());
    if (0L == checkBox)
    {
        return;
    }
    qint32 rowIndex = this->ui->tableWidget->indexAt(QPoint(checkBox->frameGeometry().x(), checkBox->frameGeometry().y())).row();
    qint32 magic = this->ui->tableWidget->item(rowIndex, 0)->text().toInt();
    ClientInfo *client = this->_clientManager.client(magic);
    if (0L != client)
    {
        client->setShow(value);
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::alertChanged(bool value)
{
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(sender());
    if (0L == checkBox)
    {
        return;
    }
    qint32 rowIndex = this->ui->tableWidget->indexAt(QPoint(checkBox->frameGeometry().x(), checkBox->frameGeometry().y())).row();
    qint32 magic = this->ui->tableWidget->item(rowIndex, 0)->text().toInt();
    ClientInfo *client = this->_clientManager.client(magic);
    if (0L != client)
    {
        client->setAlert(value);
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::colorChanged(QColor value)
{
    ColorWidget *colorWidget = qobject_cast<ColorWidget*>(sender());
    if (0L == colorWidget)
    {
        return;
    }
    qint32 rowIndex = this->ui->tableWidget->indexAt(QPoint(colorWidget->frameGeometry().x(), colorWidget->frameGeometry().y())).row();
    qint32 magic = this->ui->tableWidget->item(rowIndex, 0)->text().toInt();
    ClientInfo *client = this->_clientManager.client(magic);
    if (0L != client)
    {
        client->setColor(value);
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::editAlert(int value)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if (0L == spinBox)
    {
        return;
    }
    qint32 rowIndex = this->ui->tableWidget->indexAt(QPoint(spinBox->frameGeometry().x(), spinBox->frameGeometry().y())).row();
    qint32 magic = this->ui->tableWidget->item(rowIndex, 0)->text().toInt();
    ClientInfo *client = this->_clientManager.client(magic);
    if (0L != client)
    {
        client->setAlertThreshold(value);
    }
    this->_summarySubWindow->update();
    this->updateSubWindowMagic(magic);
}

void MainWindow::on_actionExport_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this);
    if (filePath.length() > 0)
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QVector<ClientInfo> *clients = this->_clientManager.clients();
            QTextStream out(&file);
            for (qint32 i = 0; i < clients->size(); ++i)
            {
                if ((*clients)[i].times()->size() > 0)
                {
                    out << (*clients)[i].name() << endl;
                    for (qint32 j = 0; j < (*clients)[i].times()->size(); ++j)
                    {
                        out << (*clients)[i].times()->at(j) << " ";
                        out << (*clients)[i].rtts()->at(j) << endl;
                    }
                    out << endl;
                }
            }
            file.flush();
            file.close();
        }
    }
}

void MainWindow::on_actionExit_E_triggered()
{
    this->close();
}

void MainWindow::on_actionStart_S_triggered()
{

}

void MainWindow::on_actionPause_P_triggered()
{

}

void MainWindow::on_actionStop_E_triggered()
{

}

void MainWindow::on_actionOption_O_triggered()
{

}

void MainWindow::on_actionCascade_triggered()
{
    this->ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionTile_triggered()
{
    this->ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{

}
