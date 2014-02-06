<!DOCTYPE html>

<html>
    <head>
        <link rel = "stylesheet" href = "css/see.css">
    </head>
    <body>
        <?php
            include_once "data.php";
            if(!isset($basic)) {
                $basic = $_SESSION["basic"];
            }
            $userID = $basic->UserID;
            $applications = getApplicationByUser($userID);
            for($i = 0; $i < count($applications); ++ $i) {
                switch($applications[$i]["Type"]) {
                    case 1:
                        $applications[$i]["Type"] = "站内应用";
                        break;
                    case 2:
                        $applications[$i]["Type"] = "站外应用";
                        break;
                    case 3:
                        $applications[$i]["Type"] = "桌面应用";
                        break;
                    case 4:
                        $applications[$i]["Type"] = "核心应用";
                        break;
                }
            }
            $smarty->assign("applications", $applications);
        ?>
    </body>
</html>
