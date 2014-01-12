if (!document.getElementById("zan_global")) {
  var div = document.createElement("div");
  div.id = "zan_global";
  document.body.appendChild(div);
  
  // 在导航菜单中加入点赞按钮
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
	} else {
	  start = 0;
	  document.getElementById("zan-span").innerText = "点赞";
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
  
  // 在导航菜单中加入点赞狂魔按钮
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
	  document.getElementById("zan-monster-span").innerText = "0";
	} else {
	  start = 0;
	  monster = 0;
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
	  return;
	}
    for (var i = 0; i < links.length; ++i) {
      var strs = links[i].getAttribute('onclick').split(",");
      if (strs.length >= 5) {
	    if (links[i].innerText.indexOf("取消") < 0) {
		  if (monster) {
		    console.log(links[i].innerText);
		    links[i].click();
			++zanCount;
			document.getElementById("zan-monster-span").innerText = "" + zanCount;
			return;
		  }
		  for (var j = 0; j < zan_array.length; ++j) {
		    var id = "" + zan_array[j];
		    if (id.length > 5) {
			  if (strs[3].indexOf(id) >= 0) {
			    console.log(links[i].innerText);
				links[i].click();
				++zanCount;
				document.getElementById("zan-span").innerText = "" + zanCount;
				return;
			  }
			}
		  }
	    }
      }
    }
  }
  
  var count = -1;
  function zan() {
    if (!start) {
	  return;
	}
    count += 1;
    if (count % 10) {
	  return;
	}
    
	var newFeedsCount = document.getElementById("newFeedsCount");
	if (newFeedsCount) {
	  if (newFeedsCount.innerText != "0") {
	    document.getElementsByClassName("show-new-feed")[0].click();
	  }
	}
	
    zanLinks(document.getElementsByClassName("ilike_icon"));
	zanLinks(document.getElementsByClassName("ilike-button like"));
  }

  window.setInterval(zan, 1000);
}