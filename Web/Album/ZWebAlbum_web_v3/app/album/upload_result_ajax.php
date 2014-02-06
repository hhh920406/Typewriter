<?php
include_once "sdk/apiRequestService.php";
$result = $_POST["result"];
$photos = json_decode($result);
foreach($photos as $name => $id) {
    echo "<div class = 'photoDiv'>";
    echo "<div class = 'nameDiv'>" . $name . "</div>";
    if($id) {
        echo "<div class = 'statusDiv'>上传成功</div>";
    } else {
        echo "<div class = 'statusDiv'>上传失败</div>";
    }
    echo "</div>";
}
?>
