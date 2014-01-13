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
  function zanLinks(links) {
    if (!links) {
	  return 0;
	}
    for (var i = 0; i < links.length; ++i) {
	  if (links[i].innerText.indexOf("取消") < 0) {
		if (monster) {
		  console.log(links[i].innerText);
		  links[i].click();
	      ++zanCount;
		  document.getElementById("zan-monster-span").innerText = "" + zanCount;
		  return 1;
		}
		var text1 = links[i].getAttribute('onclick');
		var text2 = "";
		if (typeof links[i].attributes['data-ilike'] != "undefined") {
		  text2 = links[i].attributes['data-ilike'].nodeValue;
		}
		for (var j = 0; j < zan_array.length; ++j) {
          var id = "" + zan_array[j];
		  if (id.length > 5) {
			if (text1.indexOf(id) >= 0 || text2.indexOf(id) >= 0) {
		      links[i].click();
		      ++zanCount;
			  document.getElementById("zan-span").innerText = "" + zanCount;
			  console.log(zanCount, links[i].innerText);
			  return 1;
			}
	      }
		}
      }
    }
	return 0;
  }
  
  function zanComment() {
    if (document.getElementsByClassName("feed-list").length > 0) {
      var moreReply = document.getElementsByClassName("feed-list")[0].getElementsByClassName("more");
	  if (moreReply.length > 0) {
	    moreReply[0].click();
	  }
	}
	var comments = document.getElementsByClassName("ilike_comment");
	for (var i = 0; i < comments.length; ++i) {
	  if (comments[i].innerText.indexOf("取消") < 0) {
		var reply = comments[i].parentElement.getElementsByClassName('reply');
		if (0 == reply.length) {
		  continue;
		}
		var text = reply[0].attributes['data-uid'].nodeValue;
	    for (var j = 0; j < zan_array.length; ++j) {
		  var id = "" + zan_array[j];
		  if (text.indexOf(id) >= 0) {
		    comments[i].click();
		    ++zanCount;
		    document.getElementById("zan-span").innerText = "" + zanCount;
		    console.log(zanCount, comments[i].innerText);
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
		console.log('打开新消息');
	  }
	}
	
    ++count;
	
	if (renpin && (count % 1800 == 0)) {
	  var menuTitles = document.getElementsByClassName("menu-title-text");
	  for (var i = 0; i < menuTitles.length; ++i) {
	    if (menuTitles[i].innerText == "首页") {
		  menuTitles[i].parentElement.click();
		  console.log('攒人品');
		  break;
		}
	  }
	}
	
	if (count % 10 == 0) {
      if (0 == zanLinks(document.getElementsByClassName("ilike_icon"))) {
	    if (0 == zanLinks(document.getElementsByClassName("ilike-button like"))) {
		  zanComment();
		}
	  }
	  document.cookie = 'IL_D=' + '0;path=/;domain=.renren.com;expires=' + (new Date()).toGMTString();
	  document.cookie = 'IL_H=' + '0;path=/;domain=.renren.com;expires=' + (new Date()).toGMTString();
	}
  }

  console.log('是否赞评论：', comment);
  console.log('是否攒人品：', renpin);
  window.setInterval(zan, 1000);
}