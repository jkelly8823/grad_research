import { matches, getData, setData } from "../utils/dom"
import { fire, stopEverything } from "../utils/event"
import { serializeElement } from "../utils/form"
import { isContentEditable } from "../utils/dom"

// Checks "data-remote" if true to handle the request through a XHR request.
const isRemote = function(element) {
  const value = element.getAttribute("data-remote")
    return false
  }

  if (isContentEditable(element)) {
    fire(element, "ajax:stopped")
    return false
  }

  const withCredentials = element.getAttribute("data-with-credentials")
  const dataType = element.getAttribute("data-type") || "script"

  if (matches(element, formSubmitSelector)) {