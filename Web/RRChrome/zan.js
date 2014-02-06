if (!document.getElementById("zan_global")) {
    var div = document.createElement("div");
    div.id = "zan_global";
    document.body.appendChild(div);

    start = 0;
    span = document.createElement("span");
    span.id = "zan-span";
    span.className = "menu-title-text";
    span.innerText = "点赞";
    link = document.createElement("a");
    link.href = "#";
    link.appendChild(span);
    link.onclick = function() {
        if (start == 0) {
            start = 1;
            document.getElementById("zan-span").innerText = "0";
            document.getElementById("zan-monster-span").innerText = "次";
        } else {
            start = 0;
            monster = 0;
            document.getElementById("zan-span").innerText = "点赞";
            document.getElementById("zan-monster-span").innerText = "狂魔";
        }
    }
    menuTitle = document.createElement("div");
    menuTitle.className = "menu-title";
    menuTitle.appendChild(link);
    menu = document.createElement("div");
    menu.className = "menu";
    menu.appendChild(menuTitle);
    var navMenu = document.getElementsByClassName("nav-main");
    navMenu[0].appendChild(menu);

    monster = 0;
    span = document.createElement("span");
    span.id = "zan-monster-span";
    span.className = "menu-title-text";
    span.innerText = "狂魔";
    link = document.createElement("a");
    link.href = "#";
    link.appendChild(span);
    link.onclick = function() {
        if (monster == 0) {
            start = 1;
            monster = 1;
            document.getElementById("zan-span").innerText = "计数";
            document.getElementById("zan-monster-span").innerText = "0";
        } else {
            start = 0;
            monster = 0;
            document.getElementById("zan-span").innerText = "点赞";
            document.getElementById("zan-monster-span").innerText = "狂魔";
        }
    }
    menuTitle = document.createElement("div");
    menuTitle.className = "menu-title";
    menuTitle.appendChild(link);
    menu = document.createElement("div");
    menu.className = "menu";
    menu.appendChild(menuTitle);
    var navMenu = document.getElementsByClassName("nav-main");
    navMenu[0].appendChild(menu);

    var zanCount = 0;
    var zanIndex = 0;
    var zanList = new Array();
    function zanLinks() {
        if (zanIndex >= zanList.length) {
            zanIndex = 0;
            zanList = document.getElementsByClassName("ilike_icon");
            if (zanList.length == 0) {
                zanList = document.getElementsByClassName("ilike-button like");
            }
        }
        for (; zanIndex < zanList.length; ++zanIndex) {
            if (zanList[zanIndex].innerText.indexOf("取消") < 0) {
                if (monster) {
                    zanList[zanIndex++].click();
                    ++zanCount;
                    document.getElementById("zan-monster-span").innerText = "" + zanCount;
                    return 1;
                }
                var text1 = zanList[zanIndex].getAttribute('onclick');
                var text2 = "";
                if (typeof zanList[zanIndex].attributes['data-ilike'] != "undefined") {
                    text2 = zanList[zanIndex].attributes['data-ilike'].nodeValue;
                }
                for (var j = 0; j < zan_array.length; ++j) {
                    var id = "" + zan_array[j];
                    if (id.length > 5) {
                        if (text1.indexOf(id) >= 0 || text2.indexOf(id) >= 0) {
                            zanList[zanIndex++].click();
                            ++zanCount;
                            document.getElementById("zan-span").innerText = "" + zanCount;
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }

    var replyIndex = 0;
    var replyList = new Array();
    var commentIndex = 0;
    var commentList = new Array();
    function zanComment() {
        if (replyIndex >= replyList.length) {
            replyIndex = 0;
            if (document.getElementsByClassName("feed-list").length > 0) {
                replyList = document.getElementsByClassName("feed-list")[0].getElementsByClassName("more");
            }
        }
        for (; replyIndex < replyList.length; ++replyIndex) {
            replyList[replyIndex++].click();
            break;
        }
        if (commentIndex >= commentList.length) {
            commentIndex = 0;
            commentList = document.getElementsByClassName("ilike_comment");
        }
        for (; commentIndex < commentList.length; ++commentIndex) {
            if (commentList[commentIndex].innerText.indexOf("取消") < 0) {
                if (monster) {
                    commentList[commentIndex++].click();
                    ++zanCount;
                    document.getElementById("zan-span").innerText = "" + zanCount;
                    return;
                }
                var reply = commentList[commentIndex].parentElement.getElementsByClassName('reply');
                if (0 == reply.length) {
                    continue;
                }
                var text = reply[0].attributes['data-uid'].nodeValue;
                for (var j = 0; j < zan_array.length; ++j) {
                    var id = "" + zan_array[j];
                    if (text.indexOf(id) >= 0) {
                        commentList[commentIndex++].click();
                        ++zanCount;
                        document.getElementById("zan-span").innerText = "" + zanCount;
                        return;
                    }
                }
            }
        }
    }

    var count = 0;
    function zan() {
        if (!start) {
            return;
        }

        var newFeedsCount = document.getElementById("newFeedsCount");
        if (newFeedsCount) {
            if (newFeedsCount.innerText != "0") {
                document.getElementsByClassName("show-new-feed")[0].click();
            }
        }

        ++count;
        document.getElementsByClassName("menu-title-text")[1].innerText = "" + count;

        if (renpin && (count % 300 == 0)) {
            var menuTitles = document.getElementsByClassName("menu-title-text");
            for (var i = 0; i < menuTitles.length; ++i) {
                if (menuTitles[i].innerText == "首页") {
				    menuTitles[i].click();
                    menuTitles[i].parentElement.click();
                    zanIndex = 100000;
                    replyIndex = 100000;
                    commentIndex = 100000;
                    break;
                }
            }
        }

        if (count % 10 == 0) {
            if (0 == zanLinks()) {
                zanComment();
            }
            document.cookie = 'IL_D=' + '0;path=/;domain=.renren.com;expires=' + (new Date()).toGMTString();
            document.cookie = 'IL_H=' + '0;path=/;domain=.renren.com;expires=' + (new Date()).toGMTString();
        }
    }

    window.setInterval(zan, 1024);
}
