import getpass
import telnetlib

tolong= "/1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
test = 0
def test_telnet(host, port, path, method, expected_status_code):
    global test
    test += 1
    tn = telnetlib.Telnet(host, port)
    request = f"{method} {path} HTTP/1.1\r\nHost: {host}\r\n\r\n"
    tn.write(request.encode('utf-8'))
    
    response = tn.read_until(b"\r\n\r\n", timeout=10).decode('utf-8')
    
    status_code_response = response.split(" ")[1]
    if len(path) > 25:
        path = path[:22] + "..."
    print(f"TEST {test:<4} Host: {host:<20}\t Port: {port:<5}\t Path: {path:<25}\t  Method: {method:<10}"
          f"Expected Status Code: {expected_status_code:<3}\t", end="")
    print(f"Received Status Code: {status_code_response:<3}", end="")
    if (int(status_code_response) == expected_status_code):
        print("\033[92m\t\tOK\033[0m")  # Cambiado a verde
    else:
        print("\033[91m\t\tFAIL\033[0m")  # Cambiado a rojo
        print(response)
    
    tn.close()



if __name__ == "__main__":
    print('-'*190)
    print("TESTING GOOGLE0")
    print('-'*190)
    test_telnet("www.google.com", 80, "/", "GET", 200)
    print('-'*190)
    print("TESTING SERVER 1: Redirects")
    test_telnet("127.0.0.1", 8080, "/buscador", "GET", 301)
    test_telnet("127.0.0.1", 8080, "/buscador2", "GET", 302)
    test_telnet("127.0.0.1", 8080, "/buscador3", "GET", 303)
    test_telnet("127.0.0.1", 8080, "/buscador4", "GET", 307)
    print('-'*190)
    print("TESTING SERVER 1: Not found, Forbidden, Timeout, URI Too Long")
    test_telnet("127.0.0.1", 8080, "/files/nadaque%20encontrar.txt", "GET", 404)
    test_telnet("127.0.0.1", 8080, "/files/sinpermisos.jpg", "GET", 403)
    test_telnet("127.0.0.1", 8080, "/cgi-bin/Python/timeOut.py", "GET", 408)
    test_telnet("127.0.0.1", 8080, tolong, "GET", 414)
    test_telnet("127.0.0.1", 8080, "/", "POST", 200)
    test_telnet("127.0.0.1", 8080, "/cgi-bin/Python/calculadora.py?operation=add&num1=2&num2=40", "POST", 200)
    test_telnet("127.0.0.1", 8080, "/files/nadaque%20encontrar.txt", "POST", 404)
    test_telnet("127.0.0.1", 8080, "/files/nadaque%20encontrar.txt", "DELETE", 404)
    test_telnet("127.0.0.1", 8080, tolong, "POST", 414)
    test_telnet("127.0.0.1", 8080, tolong, "DELETE", 414)