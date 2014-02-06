{%include file="header_small.tpl" title="更新信息"%}
<div id = "sideBar">
    <article>
        <h3>
            编辑信息
        </h3>
        {%if $tab == "basic"%}
        <script src="/js/account/update_basic.js"></script>
        <a href = "/pages/account/update.php" class = "selected">
        {%else%}
        <a href = "/pages/account/update.php">
        {%/if%}
            　基本信息
        </a>
        {%if $tab == "contact"%}
        <script src="/js/account/update_contact.js"></script>
        <a href = "/pages/account/update.php?tab=contact" class = "selected">
        {%else%}
        <a href = "/pages/account/update.php?tab=contact">
        {%/if%}
            　联系方式
        </a>
    </article>
</div>
<div id = "container">
    {%if $tab == "basic"%}
        {%include file="account/update_basic.tpl"%}
    {%/if%}
</div>
{%include file="footer.tpl"%}