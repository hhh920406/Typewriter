<!DOCTYPE html>

<html>
    <head>
        <!--由于返回结果是json格式默认UTF-8编码，如果页面非UTF-8请自行进行转码。-->
        <meta charset = "utf-8">
        <title>SDK Demo</title>
    </head>

    <html>
        <?php
            include_once "apiRequestService.php";

            $api = new ApiRequestService();
            echo "Token: <br/>";
            print_r($result = $api->getUserToken("Monkey012"));
            echo "<br/>User.Basic: <br/>";
            print_r($api->getUserBasic());
        ?>
    </html>
</html>


