<?php
/*
In PHP, we can use the standard cURL libraries to make HTTP requests. First, we define the baseURL, searchText, and bearerToken variables. Then, we construct the complete URL with the encoded search text using template literals.

Next we create a new curl instance and add the required headers. The result of the curl request is decode into an array after which the first hs_code element is printed to the console.
*/

$baseURL = "https://api.fractus-ai.com/api/search";
$searchText = "horse";
$bearerToken = "your-bearer-token";

$url = $baseURL."?q=".urlencode($searchText);

$ch = curl_init();
curl_setopt($ch,CURLOPT_URL,$url);
curl_setopt($ch,CURLOPT_CUSTOMREQUEST,"GET"); 
curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
curl_setopt($ch,CURLOPT_FOLLOWLOCATION,true);
$headers = [
    "Accept: application/json",
    "Authorization: Bearer {$bearerToken}"
];
curl_setopt($ch,CURLOPT_HTTPHEADER,$headers);
$server_output = curl_exec($ch);
curl_close($ch);

$json = json_decode($server_output,true);

print "Found HS code: {$json['data'][0]['hs_code']}\n";
?>
