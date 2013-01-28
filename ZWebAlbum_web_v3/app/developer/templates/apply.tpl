<div id = "formDiv">
    <div class = "rowHead">
        申请新应用
    </div>
    <div class = "rowDescription">
        <hr/>
    </div>

    <div class = "rowInput">
        <div class = "columnText">
            申请应用代号：
        </div>
        <div class = "columnInput">
            <input id = "Text_Symbol" type = "text" onkeyup = "judgeSymbol()"></input>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Symbol"></div>
        </div>
    </div>
    <div class = "rowDescription">
        <div class = "columnDescription">
            只能输入大小写英文字母、数字和下划线，应用的名称不能与已有的应用名称相同。
        </div>
    </div>
    
    <div class = "rowInput">
        <div class = "columnText"></div>
        <div class = "columnInput">
            <input id = "Button_Symbol" type = "button" value = "检测是否已经存在" disabled = "disabled" onclick = "judgeExistSymbol()"></input>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Exist_Symbol"></div>
        </div>
    </div>

    <div class = "rowInput">
        <div class = "columnText">
            应用名称：
        </div>
        <div class = "columnInput">
            <input id = "Text_Name" type = "text" onkeyup = "judgeName()"></input>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Name"></div>
        </div>
    </div>
    <div class = "rowDescription">
        <div class = "columnDescription">
            应用名称不能为空，不能与已有应用名冲突，不可以出现半角空格，可以输入中文。
        </div>
    </div>

    <div class = "rowInput">
        <div class = "columnText"></div>
        <div class = "columnInput">
            <input id = "Button_Name" type = "button" value = "检测是否已经存在" disabled = "disabled" onclick = "judgeExistName()"></input>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Exist_Name"></div>
        </div>
    </div>

    <div class = "rowDescription">
        <div class = "columnText">
            应用描述：
        </div>
        <div class = "columnTextArea">
            <textarea id = "TextArea_Description" onkeyup = "judgeDescription()"></textarea>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Description"></div>
        </div>
    </div>
    <div class = "rowDescription">
        <div class = "columnDescription">
            控制在240字符以内。
        </div>
    </div>

    <div class = "rowInput">
        <div class = "columnText">
            选择应用类型：
        </div>
        <div class = "columnInput">
            <select id = "Select_Type">
                <option value = "Inside">站内应用</option>
                <option value = "Outside">站外应用</option>
                <option value = "Desktop">客户端应用</option>
                {if $basic["type"] == "Admin" || $basic["type"] == "Super Admin"}
                <option value = "Core">核心应用</option>
                {/if}
            </select>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Type"></div>
        </div>
    </div>
    <div class = "rowDescription">
        <div class = "columnDescription">
            站内应用：只能由php编写，可以上传到站内服务器中，在iframe中运行。
            <br/>
            站外应用：使用自己的服务器，编程语言没有限制，由iframe连接到指定的url。
            <br/>
            客户端应用：在网站之外运行，编程语言没有限制，提供程序的上传，也可由链接转向下载服务器。
            {if $basic["type"] == "Admin" || $basic["type"] == "Super Admin"}
            <br/>
            核心应用：只有管理员级别才可以进行开发，默认即可获得用户全部许可。
            {/if}
        </div>
    </div>

    <div class = "rowDescription">
        <div class = "columnText">
            用户许可：
        </div>
        <div class = "columnSelect">
            <input id = "Checkbox_user_basic" type = "checkbox" checked = "true" >获取用户的基础信息</input>
            <br/>
            <input type = "checkbox">获取相册列表和照片列表</input>
            <br/>
            <input type = "checkbox">创建相册和添加照片</input>
            <br/>
            <input type = "checkbox">删除相册或照片</input>
        </div>
        <div class = "columnStatus">
            <div id = "Status_Permission"></div>
        </div>
    </div>

    <div class = "rowDescription">
        <hr/>
    </div>
    <div class = "rowSubmit">
        <input type = "button" value = "申　请" onclick = "apply()"></input>
        <div class = "columnInput">
            <div id = "Status_Apply"></div>
        </div>
    </div>
</div>