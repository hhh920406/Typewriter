<?php
    /**
     * The index of the website.
     * @author ZHG
     */
    include_once "init.php";
    // Assign values and display. 
    $smarty->assign('userID', $userID);
    $smarty->assign('userNickname', $userNickname);
    $smarty->display('index.tpl');
?>
