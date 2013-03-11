<!DOCTYPE html>
<html>
    <head>
        <meta charset = UTF-8>
        <title>商品搜索</title>
        <link rel = stylesheet href = ../../styles/search/index.css>
        <script src = ../../scripts/util/jquery.js></script>
        <script src = ../../scripts/search/index.js></script>
    </head>
    <body>
        <div class = searchDiv>
            <a href = # title = 输入搜索内容>
                <input type = text class = searchText></input>
            </a>
            <a href = # title = 通过文字搜索>
                <input type = button class = searchButton></input>
            </a>
            <a href = # title = 通过图片搜索>
                <input type = button class = searchImage></input>
            </a>
            <div class = searchConfigDiv>
                <a id = "Link_Config" href = # title = 搜索设置>
                    搜索设置
                </a>
            </div>
        </div>
        <div class = searchConfigDetailDiv>
            <div>
                商品价格范围：
            </div>
            <div>
                <span>起始价格：</span>
                <input id = Input_Price_Start type = text></input>
                <span>终止价格：</span>
                <input id = Input_Price_End type = text></input>
            </div>
        </div>
    </body>
</html>