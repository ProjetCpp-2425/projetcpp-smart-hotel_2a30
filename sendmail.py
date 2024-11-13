import sys
import webbrowser

if len(sys.argv) < 5:
    print("Usage: sendmail.py <recipient_email> <fullname> <position> <cin>")
    sys.exit(1)

recipient_email = sys.argv[1]
fullname = sys.argv[2]
position = sys.argv[3]
cin = sys.argv[4]

# Create the email content
subject = f"Employee Information for {fullname}"
body = f"Full Name: {fullname}\nPosition: {position}\nCIN: {cin}"

# Format the mailto: link
mailto_link = f"mailto:{recipient_email}?subject={subject}&body={body}"

# Open the default email client with the pre-filled email
webbrowser.open(mailto_link)
