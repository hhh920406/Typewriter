{%include file = "header_small.tpl" title = "应用"%}
<div id = "sideBar">
    <article>
        <h3>
            管理应用
        </h3>
        {%if $tab == "basic"%}
        <a href = "/pages/application/index.php" class = "selected">
        {%else%}
        <a href = "/pages/application/index.php">
        {%/if%}
            　我的应用
        </a>
        {%if $tab == "contact"%}
        <a href = "/pages/application/index.php?tab=add" class = "selected">
        {%else%}
        <a href = "/pages/application/index.php?tab=add">
        {%/if%}
            　添加应用
        </a>
        <a href = "/pages/application/application.php?appname=developer">
            　开发应用
        </a>
    </article>
</div>
{%include file = "footer.tpl"%}