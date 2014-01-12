chrome.webNavigation.onDOMContentLoaded.addListener(function(details) {
  if (details.url.indexOf("renren.com") >= 0) {
    chrome.cookies.remove({url: 'http://renren.com', name: 'IL_D'});
    chrome.cookies.remove({url: 'http://renren.com', name: 'IL_H'});
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