/**
 * @Author: Thibault Napoléon <Imothep>
 * @Company: ISEN Yncréa Ouest
 * @Email: thibault.napoleon@isen-ouest.yncrea.fr
 * @Created Date: 23-Jan-2018 - 17:00:53
 * @Last Modified: 24-Jan-2018 - 17:03:23
 */

'use strict';

//------------------------------------------------------------------------------
//--- ajaxRequest --------------------------------------------------------------
//------------------------------------------------------------------------------
// Perform an Ajax request.
// \param type The type of the request (GET, DELETE, POST, PUT).
// \param request The request with the data.
// \param callback The callback to call where the request is successful.
// \param data The data associated with the request.
function ajaxRequest(type, request, callback, data= null)
{
  var xhr;
  // Create XML HTTP request.
  xhr = new XMLHttpRequest();
    if (type == 'GET' && data != null)
        request += '?' + data;
  xhr.open(type, request, true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.setRequestHeader('Authorization','Bearer '+ Cookies.get('token'));
  // Add the onload function.
  xhr.onload = function ()
  {
    switch (xhr.status)
    {
      case 200:
      case 201:
        callback(xhr.responseText);
        break;
      default:
        httpErrors(xhr.status);
    }
  };

  // Send XML HTTP request.
  xhr.send(data);
}

//------------------------------------------------------------------------------
//--- httpErrors ---------------------------------------------------------------
//------------------------------------------------------------------------------
// Display a message corresponding to an Http error code.
// \param errorNumber the error code.
function httpErrors(errorNumber)
{
  var text;

  text = '<div class="alert alert-danger" role="alert">';
  text += '<span class="glyphicon glyphicon-exclamation-sign"></span>';
  switch (errorNumber)
  {
    case 400:
      // Bad request.
      text += '<strong> Bad request</strong>';
      break;
    case 401:
      // Unauthorized.
      text += '<strong> Unauthorized</strong>';
      break;
    case 403:
      // Forbidden.
      text += '<strong> Forbidden</strong>';
      break;
    case 404:
      // Ressource not found.
      text += '<strong> Page not found</strong>';
      break;
    case 500:
      // Internal server error.
      text += '<strong> Internal server error</strong>';
      break;
    case 503:
      // Service unavailable.
      text += '<strong> Service unavailable</strong>';
      break;
    default:
      text += '<strong> error HTTP ' + errorNumber + '</strong>';
      break;
  }
  text += '</div>';
  $('#errors').html(text);
}
