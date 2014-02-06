<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
    </head>
    <body>
        <?php
        function check_wap() {
            if (isset ($_SERVER['HTTP_X_WAP_PROFILE'])) {
                return true;
            }
            if (isset ($_SERVER['HTTP_VIA'])) {
                return stristr($_SERVER['HTTP_VIA'], "wap") ? true : false;
            }
            if (isset ($_SERVER['HTTP_USER_AGENT'])) {
                $clientkeywords = array ('nokia','sony','ericsson','mot','samsung','htc','sgh','lg','sharp','sie-','philips','panasonic','alcatel','lenovo','iphone','ipod','blackberry','meizu','android','netfront','symbian','ucweb','windowsce','palm','operamini', 'operamobi','openwave','nexusone','cldc','midp','wap','mobile');
                if (preg_match("/(" . implode('|', $clientkeywords) . ")/i", strtolower($_SERVER['HTTP_USER_AGENT']))) {
                    return true;
                }
            }
            if (isset ($_SERVER['HTTP_ACCEPT'])) {
                if ((strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') !== false) && (strpos($_SERVER['HTTP_ACCEPT'], 'text/html') === false || (strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') < strpos($_SERVER['HTTP_ACCEPT'], 'text/html')))) {
                    return true;
                }
            }
            return false;
        }
        if (check_wap()) {
            header("Location: indexwap1.php");
        } else {
            header("Location: index2.php");
        }
        ?>
    </body>
</html>