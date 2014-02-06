<div id = "sideBar">
    <artical>
        <h3>开发者</h3>
        <a {if $tab == ""}class = "selected"{/if} href = {$url}>
            　已有应用
        </a>
        <a {if $tab == "apply"}class = "selected"{/if} href = {$url}&tab=apply>
            　申请应用
        </a>
        <a {if $tab == "doc"}class = "selected"{/if} href = {$url}&tab=doc>
            　开发文档
        </a>
        <a {if $tab == "download"}class = "selected"{/if} href = {$url}&tab=download>
            　SDK下载
        </a>
    </artical>
</div>