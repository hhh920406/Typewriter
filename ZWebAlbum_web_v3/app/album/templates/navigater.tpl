<div id = "sideBar">
    <artical>
        <h3>相册</h3>
        <a {if $tab == ""}class = "selected"{/if} href = {$url}>
            　查看相册
        </a>
        <a {if $tab == "new"}class = "selected"{/if} href = {$url}&tab=new>
            　新建相册
        </a>
        <a {if $tab == "upload"}class = "selected"{/if} href = {$url}&tab=upload>
            　上传照片
        </a>
    </artical>
</div>