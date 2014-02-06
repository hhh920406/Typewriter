<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品信息测试</title>
    </head>
    <body>
        <?php
        /**
         * 对商品信息的测试。
         * @author ZHG <CyberZHG@gmail.com>
         */
        require_once "DataSourceTaobao.class.php";
        require_once "test.php";
        $source = new DataSourceTaobao();
        $result = $source->getItemList(0, 50004889, "", 0, 0, 1, 10);
        printArrayWithTable($result);
        ?>
    </body>
</html>
