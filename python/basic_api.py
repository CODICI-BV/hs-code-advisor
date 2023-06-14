#In Python, we use the requests library to make HTTP requests.
#The requests.get() function is used to send a GET request to the specified URL
#with the headers. The response is then converted to JSON format using
#the .json() method.
#
#Note that you may need to install the requests library if you don't have it already.
#You can install it by running pip install requests in your terminal or command prompt.

import requests

baseURL = "https://api.fractus-ai.com/api/search"
searchText = "horse"
bearerToken = "your-bearer-token"

url = baseURL + "?q=" + searchText
headers = {
    "Accept": "application/json",
    "Authorization": "Bearer " + bearerToken
}

response = requests.get(url, headers=headers)
json_data = response.json()

print("Found HS code:", json_data["data"][0]["hs_code"])
