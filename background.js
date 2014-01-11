chrome.webNavigation.onDOMContentLoaded.addListener(function(details) {
  if (details.url.indexOf("renren.com") >= 0) {
    chrome.storage.sync.get('start', function(item) {
	  console.log(item.start);
	  if (item.start) {
        chrome.storage.sync.get('ids', function(items) {
	      code = "zan_array = [";
          if (items.ids) {
            for (var i = 0; i < items.ids.length; ++i) {
		      if (i > 0) {
		        code += ",";
		      }
		      code += items.ids[i];
		    }
	      }
	      code += "];";
	      chrome.tabs.executeScript(details.tabId, {code: code});
	      chrome.tabs.executeScript(details.tabId, {file: "zan.js"});
	    });
	  }
    });
  }
});