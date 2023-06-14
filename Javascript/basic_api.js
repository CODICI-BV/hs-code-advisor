/*
In JavaScript, we can use the axios library to make HTTP requests. First, we define the baseURL, searchText, and bearerToken variables. Then, we construct the complete URL with the encoded search text using template literals.

Next, we define the headers object with the necessary headers. We use axios.get() to send a GET request to the specified URL with the headers. The response is handled using Promises: if the request is successful, the then block extracts the JSON data from the response and logs the HS code. If an error occurs, the catch block logs the error message.

Note that in order to run this JavaScript code, you'll need to have the axios library installed. You can install it by running npm install axios or yarn add axios depending on your package manager.
*/

const axios = require('axios');

const baseURL = "https://api.fractus-ai.com/api/search";
const searchText = "horse";
const bearerToken = "your-bearer-token";

const url = `${baseURL}?q=${encodeURIComponent(searchText)}`;
const headers = {
  "Accept": "application/json",
  "Authorization": `Bearer ${bearerToken}`
};

axios.get(url, { headers })
  .then(response => {
    const json = response.data;
    console.log("Found HS code:", json.data[0].hs_code);
  })
  .catch(error => {
    console.error("An error occurred:", error);
  });
