if (!document.getElementById("zan_global")) {
  var div = document.createElement("div");
  div.id = "zan_global";
  document.body.appendChild(div);

  console.log('Inside');
  window.setInterval(function() {
    var links = document.getElementsByClassName("ilike_icon");
    console.log("Finding...", links.length);
    for (var i = 0; i < links.length; ++i) {
      var strs = links[i].getAttribute('onclick').split(",");
      if (strs.length >= 5) {
	    if (links[i].innerText.indexOf("取消") < 0) {
          if (strs[3].indexOf("283858273") >= 0 || strs[3].indexOf("287105729") >= 0) {
		    console.log(i, links[i].innerText);
	        links[i].click();
		    return;
	      }
	    }
      }
    }
    window.location.reload();
    console.log("Reload.");
  }, 10000);
}