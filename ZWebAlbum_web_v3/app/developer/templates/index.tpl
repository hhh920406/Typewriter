{include file = "header.tpl"}
{if $tab == "basic"}
    {if $appid}
        <script src = "js/form.js"></script>
        {include file = "update.tpl"}
    {else}
        {include file = "see.tpl"}
    {/if}
{elseif $tab == "apply"}
    <script src = "js/form.js"></script>
    <script src = "js/apply.js"></script>
    {include file = "apply.tpl"}
{elseif $tab == "doc"}
    {include file = "doc.tpl"}
{elseif $tab == "download"}
    {include file = "download.tpl"}
{/if}
{include file = "footer.tpl"}