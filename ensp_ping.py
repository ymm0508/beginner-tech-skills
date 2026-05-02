import subprocess
import platform

def ping_ip(ip):
    param = "-n" if platform.system() == "Windows" else "-c"
    command = ["ping",param,"4",ip]

    result = subprocess.run(command, capture_output=True, text=True)

    if result.returncode == 0:
        return f"{ip}✔ 可达"
    else:
        return f"{ip}❌ 不可达"

if __name__ =="__main__":
    devices = {
        "192.168.30.150",
        "192.168.10.10",
        "192.168.20.20"
    }

for ip in devices:
    print(ping_ip(ip))