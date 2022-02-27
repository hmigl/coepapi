![coepapi](https://user-images.githubusercontent.com/88746406/155742706-a4cb5c79-84b7-4a9e-a9cf-ef3f89fd4e46.png)

# A simple and easy to use REST API that fetches data from [Brasil API](https://brasilapi.com.br/)

---
## Built with
- [mongoose](https://github.com/cesanta/mongoose)
- [libcurl](https://curl.se/libcurl/)
- [GNU make](https://www.gnu.org/software/make/)

### And heavily tested with [Insomnia](https://insomnia.rest/)
---
## Why is this useful?
Suppose you'd like to know the details about a certain location.
A [CEP](https://www.significados.com.br/cep/) of that place is the only
thing needed here. Give it to coepapi and it's done. **It's fast. It's simple.**
There's no need to open a browser to search for it. In fact, all you need
is a terminal.


## How to start using it?

```bash
# Clone this repository
git clone https://github.com/42sp/42labs-selection-process-v2-hmigl.git coepapi

# Go into the cloned folder
cd coepapi

# Run make
make

# Execute the program
./coepapi
```
#### It's now running locally at `http://localhost:8000`
---

## What coepapi can do
- Handle requests at endpoints and respond with JSON

### GET `/cep/v2/70165900` will give you
```json
{
	"cep": "70165900",
	"state": "DF",
	"city": "Brasília",
	"neighborhood": "Zona Cívico-Administrativa",
	"street": "Praça dos Três Poderes",
	"service": "viacep",
	"location": {
		"type": "Point",
		"coordinates": {
			"longitude": "-47.85998",
			"latitude": "-15.8008449"
		}
	}
}
```

### GET `/` will show you the right endpoint to make a request
```json
{
	"location": "/cep/v2/"
}
```

- Inform you immediately in case a given URI does not work, or some
method is not allowed. In these cases, the proper HTTP response status code
will be available.


For instance, both of the requests below you give you a `404 Not Found`
status code:
### GET `/cep/v2/12345678`
### GET `/uri/does/not/exist`


Here, since PUT is not yet implemented, the code you'll receive is `405
Method not Allowed`:
### PUT `/cep/v2/70165900`

> Learn more about these status codes [here](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status)

- [Log](https://github.com/42sp/42labs-selection-process-v2-hmigl/blob/main/.log/server_log)
useful information about each request:
	- Requests timestamps
	- Used method
	- Used URI
	- Received status code


> You can then make any use of the information using the [CLI](https://github.com/42sp/42labs-selection-process-v2-hmigl/tree/main/cli#readme)
that is also part of this repository

## Updates
This project will be regularly updated with code optimization and bug fixes.

## Contribute
If you like this project, feel free to contribute!
