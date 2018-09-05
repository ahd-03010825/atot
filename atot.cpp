#include "atot.h"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/FilePartSource.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Timespan.h>

#include <fstream>
#include <string>

namespace {

std::string API_HOST = "localhost";
int API_PORT = 3000;
int API_TIMEOUT = 30;

} // namespace

using namespace Poco::Dynamic;
using namespace Poco::JSON;
using namespace Poco::Net;
using namespace Poco;

extern "C" {

void atot_set_host_and_port(const char* host, int port)
{
	API_HOST = host;
	API_PORT = port;
}

void atot_set_timeout(int timeout_sec)
{
	API_TIMEOUT = timeout_sec;
}

int atot_recognize(const char* wav_filename, const char* text_filename)
{
	HTTPRequest request(HTTPRequest::HTTP_POST, "/");

	HTMLForm form;
	form.setEncoding(HTMLForm::ENCODING_MULTIPART);
	form.addPart("file", new FilePartSource(wav_filename));
	form.prepareSubmit(request);

	// send request
	HTTPClientSession httpSession(API_HOST, API_PORT);
	httpSession.setTimeout(Timespan(API_TIMEOUT, 0));
	form.write(httpSession.sendRequest(request));

	// @TODO error handling not finished yet.
	HTTPResponse res;
	std::istream& is = httpSession.receiveResponse(res);

	Parser parser;
	Var result = parser.parse(is);
	Object::Ptr obj = result.extract<Object::Ptr>();
	std::string text = obj->getValue<std::string>("text");

	std::ofstream stream;
	stream.open(text_filename);

	stream << text << std::endl;
	stream.close();

	return 0;
}

} // extern "C"
