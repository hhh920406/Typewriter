$(function() {
    $("#Button_Wap_Image").click(function() {
        $(".searchDiv").slideDown(500);
        $(".settingDiv").hide(400);
        $(".resultDiv").hide(400);
        $(".historyDiv").hide(400);
        $("#Button_Wap_Image").prop("class", "selected");
        $("#Button_Wap_Setting").removeProp("class");
        $("#Button_Wap_Result").removeProp("class");
        $("#Button_Wap_History").removeProp("class");
    });
    $("#Button_Wap_Setting").click(function() {
        $(".searchDiv").slideUp(400);
        $(".settingDiv").slideDown(500);
        $(".resultDiv").slideUp(400);
        $(".historyDiv").slideUp(400);
        $("#Button_Wap_Image").removeProp("class");
        $("#Button_Wap_Setting").prop("class", "selected");
        $("#Button_Wap_Result").removeProp("class");
        $("#Button_Wap_History").removeProp("class");
    });
    $("#Button_Wap_Result").click(function() {
        $(".searchDiv").slideUp(400);
        $(".settingDiv").slideUp(400);
        $(".resultDiv").slideDown(500);
        $(".historyDiv").slideUp(400);
        $("#Button_Wap_Image").removeProp("class");
        $("#Button_Wap_Setting").removeProp("class");
        $("#Button_Wap_Result").prop("class", "selected");
        $("#Button_Wap_History").removeProp("class");
    });
    $("#Button_Wap_History").click(function() {
        $(".searchDiv").slideUp(400);
        $(".settingDiv").slideUp(400);
        $(".resultDiv").slideUp(400);
        $(".historyDiv").slideDown(500);
        $("#Button_Wap_Image").removeProp("class");
        $("#Button_Wap_Setting").removeProp("class");
        $("#Button_Wap_Result").removeProp("class");
        $("#Button_Wap_History").prop("class", "selected");
    });
    $("#Link_Upload").click(function() {
        $("#Div_Upload").slideDown(500);
        $("#Div_Sketch").slideUp(500);
    });
    $("#Link_Sketch").click(function() {
        $("#Div_Upload").slideUp(500);
        $("#Div_Sketch").slideDown(500);
    });
    $("#Div_Upload_Click").click(function() {
        $("#File_Upload").click();
    });
});