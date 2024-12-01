import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
SMTP_SERVER = 'smtp.qq.com' 
SMTP_PORT = 587   
EMAIL_ADDRESS = 'wallwayj@qq.com'
EMAIL_PASSWORD = 'purmsejdbznnejbf'   
image_paths = ["/home/pi/temp/myjob/5.jpg"]
image_stranger = ["./5.jpg"]
image_fire = ["./4.jpg"]

def send_email_text(subject, body, to_email):
    msg = MIMEMultipart()
    msg['Subject'] = subject
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = to_email

    text_part = MIMEText(body, 'plain')
    msg.attach(text_part)

    try:      
        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.starttls()  
        server.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
        server.sendmail(EMAIL_ADDRESS, to_email, msg.as_string())
        print("Email sent successfully.")
    except Exception as e:
        print("Failed to send email:", e)
    finally:
        server.quit()
def send_email_task(subject, body, to_email, image_paths=None):  
    msg = MIMEMultipart()
    msg['Subject'] = subject
    msg['From'] = EMAIL_ADDRESS
    msg['To'] = to_email
    text_part = MIMEText(body)
    msg.attach(text_part)
    if image_paths:
        for image_path in image_paths:
            with open(image_path, 'rb') as img_file:
                image_part = MIMEImage(img_file.read(), name=image_path)
            msg.attach(image_part)
    try:      
        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.starttls()  
        server.login(EMAIL_ADDRESS, EMAIL_PASSWORD)
        server.sendmail(EMAIL_ADDRESS, to_email, msg.as_string())
        print("Email sent successfully.")
    except Exception as e:
        print("Failed to send email:", e)
    finally:
        server.quit()
        
def send_alarm(who):
    if who==0:
        send_email_task("Abnormal environmental detection", "Suspected fire, please note! - from intelligent security", "3301934971@qq.com", image_fire)        
    elif who==1:
        send_email_task("Unknown personnel", "Detect unknown personnel, please be aware-- From intelligent security", "3301934971@qq.com", image_stranger)
    elif who==2:
        send_email_text("Abnormal environmental detection", "Detected abnormal gas, please pay attention-- From intelligent security ", "3301934971@qq.com") 
        
        
        
 
'''   
send_email_task("tiltle", "text ", "3301934971@qq.com",image_paths)      
  
#send_email("THE", "TRY FIRST ", "3301934971@qq.com")
'''
