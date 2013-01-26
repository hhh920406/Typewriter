{include file = "header.tpl"}
{if $tab == "basic"}
    {if $appid}
        {include file = "update.tpl"}
    {else}
        {include file = "see.tpl"}
    {/if}
{elseif $tab == "apply"}
    {include file = "apply.tpl"}
{elseif $tab == "doc"}
    {include file = "doc.tpl"}
{elseif $tab == "download"}
    {include file = "download.tpl"}
{/if}
{include file = "footer.tpl"}