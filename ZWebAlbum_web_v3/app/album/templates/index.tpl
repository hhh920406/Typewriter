{include file = "header.tpl"}
{if $tab == ""}
    {if $tabsub == "album_list"}
        {include file = "album_list.tpl"}
    {elseif $tabsub == "photo_list"}
        {include file = "photo_list.tpl"}
    {elseif $tabsub == "photo"}
        {include file = "photo.tpl"}
    {/if}
{elseif $tab == "new"}
    {include file = "new.tpl"}
{elseif $tab == "upload"}
    {include file = "upload.tpl"}
{/if}
{include file = "footer.tpl"}