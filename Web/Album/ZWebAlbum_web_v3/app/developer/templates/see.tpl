<h3>
    　我的应用
</h3>
<hr/>
{foreach item = application from = $applications}
<div id = Div_App_{$application.ApplicationID} class = "fieldsetDiv">
    <fieldset>
        <legend>
            {$application.Symbol}
        </legend>
        <div>
            API Key：{$application.APIKey}
        </div>
        <div>
            应用名称：{$application.Name}
        </div>
        <div>
            应用描述：{$application.Description}
        </div>
        <div>
            应用类型：{$application.Type}
        </div>
        <div class = "buttonDiv">
            <input readonly = "readonly" value = "编辑" class = "editButton" onclick = appEdit({$application.ApplicationID}) />
            <input readonly = "readonly" value = "删除" class = "deleteButton" onclick = appDelete({$application.ApplicationID}) />
        </div>
    </fieldset>
</div>
{/foreach}
<hr/>