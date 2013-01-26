<?php
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/application/application_token.php";
include_once $_SERVER["DOCUMENT_ROOT"] . "/api/account/account_user.php";
$name = Application_Token::getUserName($token);
$userArray = Account_User::getUserByName($name);
foreach($userArray as $user) {
    $basic = array(
        "UserID" => $user["UserID"],
        "Name" => $user["Name"],
        "Nickname" => $user["Nickname"],
        "Type" => Account_User::getTypeMessage($user["Type"])
    );
    echo json_encode($basic);
    break;
}
?>
