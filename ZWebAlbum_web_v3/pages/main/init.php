<?php
    /**
     * The initial file of every page.
     * @author ZHG
     */
    include_once "account_init.php";
    include_once "smarty_init.php";
    $smarty->assign("userID", $userID);
    $smarty->assign("userNickName", $userNickname);
?>
