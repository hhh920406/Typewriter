if (!document.getElementById("zan_global")) {
  var div = document.createElement("div");
  div.id = "zan_global";
  document.body.appendChild(div);
  
  var count = -1;
  
  function zan() {
    count += 1;
    if (count % 10) {
	  return;
	}
    var links = document.getElementsByClassName("ilike_icon");
    for (var i = 0; i < links.length; ++i) {
      var strs = links[i].getAttribute('onclick').split(",");
      if (strs.length >= 5) {
	    if (links[i].innerText.indexOf("取消") < 0) {
		  for (var j = 0; j < zan_array.length; ++j) {
		    var id = "" + zan_array[j];
		    if (id.length > 5) {
			  if (strs[3].indexOf(id) >= 0) {
			    console.log(links[i].innerText);
				links[i].click();
				return;
			  }
			}
		  }
	    }
      }
    }
	if (count > 10) {
      window.location.reload();
	}
  }

  window.setInterval(zan, 1000);
}