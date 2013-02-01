{if $page != 1}
    <a href = {$pageURL}&page=1>首页</a>
{else}
    首页
{/if}

{if $page > 1}
    <a href = {$pageURL}&page={$page - 1}>上一页</a>
{else}
    上一页
{/if}

{if $page - 3 > 0}
    ...
{/if}

{if $page - 2 > 0}
    <a href = {$pageURL}&page={$page - 2}>{$page - 2}</a>
{/if}

{if $page - 1 > 0}
    <a href = {$pageURL}&page={$page - 1}>{$page - 1}</a>
{/if}

{$page}

{if $page + 1 < $maxPage}
    <a href = {$pageURL}&page={$page + 1}>{$page + 1}</a>
{/if}

{if $page + 2 < $maxPage}
    <a href = {$pageURL}&page={$page + 2}>{$page + 2}</a>
{/if}

{if $page + 3 < $maxPage}
    ...
{/if}

{if $page < $maxPage}
    <a href = {$pageURL}&page={$page + 1}>下一页</a>
{else}
    下一页
{/if}

{if $page != $maxPage}
    <a href = {$pageURL}&page={$maxPage}>尾页</a>
{else}
    尾页
{/if}