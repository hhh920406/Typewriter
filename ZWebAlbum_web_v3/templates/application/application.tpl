{%include file = "header_small.tpl" title = "应用"%}
{%if $apppath == ""%}
<h2>
    应用不存在
</h2>
{%else%}
<iframe id = "appFrame" scrolling = "no" class = "appFrame" onLoad="tuneHeight()" src = {%$apppath%} >
</iframe>
{%/if%}
{%include file = "footer.tpl"%}