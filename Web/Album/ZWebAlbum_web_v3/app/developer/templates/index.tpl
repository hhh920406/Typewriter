{include file = "header.tpl"}
<script src = "js/ajax.js"></script>
<script src = "js/querystring.js"></script>
{include file = "dialog.tpl"}
{if $tab == ""}
    {if $appid}
        <script src = "js/form.js"></script>
        <script src = "js/update.js"></script>
        {include file = "update.tpl"}
    {else}
        <script src = "js/see.js"></script>
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