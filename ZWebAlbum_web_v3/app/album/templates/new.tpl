<div class = "newDiv">
    <div class = "newHead">
        新建相册
        <hr/>
    </div>

    <div class = "newLine">
        <div class = "newText">
            相册名：
        </div>
        <div class = "newInput">
            <input id = "Text_Name" type = "text" onkeyup = "judgeNameExist()" ></input>
        </div>
        <div class = "newStatus">
            <div id = "Status_Name"></div>
        </div>
    </div>

    <div class = "newLine">
        <div class = "newText">
            相册名称：
        </div>
        <div class = "newTextArea">
            <textarea id = "TextArea_Description" onkeyup = "judgeDescription()"></textarea>
        </div>
        <div class = "newStatus">
            <div id = "Status_Description"></div>
        </div>
    </div>

    <div class = "newLine">
        <hr/>
    </div>

    <div class = "newLine">
        <div class = "newText"></div>
        <div class = "newInput">
            <input type = "button" value = "新　建" onclick = "createAlbum()"/>
        </div>
        <div class = "newStatus">
            <div id = "Status_Create"></div>
        </div>
    </div>
</div>