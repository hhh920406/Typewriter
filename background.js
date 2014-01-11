chrome.webNavigation.onDOMContentLoaded.addListener(function(details) {
  if (details.url.indexOf("renren.com") >= 0) {
	chrome.tabs.executeScript(details.tabId, {file: "zan.js"});
  }
});