<?php
    /**
     * The index of the website.
     * @author ZHG
     */
    require('Smarty.class.php');
    $smarty = new Smarty;
    //$smarty->force_compile = true;
    $smarty->debugging = true;
    $smarty->caching = true;
    $smarty->cache_lifetime = 120;
    // Assign values and display. 
    $smarty->display('index.tpl');
?>
