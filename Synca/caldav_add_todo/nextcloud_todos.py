import caldav, uuid
from oauth2client import client, tools, file
from requests.auth import AuthBase
from datetime import datetime, timedelta
import argparse

date_format = "%Y%m%dT%H%M%S"
calendar_name = "Daily"

def get_daily(calendars) :
  for c in calendars:
    if c.name == calendar_name :
        return c
  return none

class OAuth(AuthBase):
    def __init__(self, credentials):
        self.credentials = credentials

    def __call__(self, r):
        self.credentials.apply(r.headers)
        return r

def dav_authentificate(args):
    client_secrets = args.client_secrets
    flow = client.flow_from_clientsecrets(
            client_secrets, scope="", message=tools.message_if_missing(client_secrets)
    )

    storage = file.Storage('calendar_credentials.dat') 
    credentials = storage.get()

    if credentials is None or credentials.invalid:
        credentials = tools.run_flow(flow, storage, args)

    url = args.url
    caldav_client = caldav.DAVClient(url, auth=OAuth(credentials))
    return caldav_client


todo_template = """
BEGIN:VTODO
DTSTAMP:{DTSTAMP}
UID:{UID}
CREATED:{CREATED}
SEQUENCE:1
LAST-MODIFIED:{DTSTAMP}
SUMMARY:{SUMMARY}
DESCRIPTION:{DESCRIPTION}
STATUS:NEEDS-ACTION
DUE;TZID={TIME_ZONE}:{DUE}
DTSTART;TZID={TIME_ZONE}:{DTSTART}
END:VTODO
"""

calendar_wrapper = """
BEGIN:VCALENDAR
VERSION:2.0
PRODID: alexkutsan
{}
END:VCALENDAR
"""


def Todo(summary, description, dtstart, due, timezone="Europe/Kiev"):
    dtstart = dtstart.strftime(date_format)
    due = due.strftime(date_format)
    uid = str(uuid.uuid4())
    created = datetime.now().strftime(date_format)
    return todo_template.format(DTSTAMP = created, UID = uid, CREATED = created, DESCRIPTION = description, TIME_ZONE = timezone, DTSTART = dtstart, SUMMARY = summary, DUE = due)


def main(args):
    if (args.client_secrets):
        caldav_client = dav_authentificate(args)
    else:
        caldav_client = caldav.DAVClient(args.url)

    principal = caldav_client.principal()
    calendar = get_daily(principal.calendars())
    if None == calendar :
        print(" Daily calendar not found")
    print(len(calendar.todos()))
    dtstamp =  datetime.strptime(args.datetime, date_format) 
    t = Todo(summary = args.summary,
         description = args.description,
         dtstart = dtstamp,
         due = dtstamp + timedelta(hours=1))
    vcal = calendar_wrapper.format(t)
    calendar.add_todo(vcal)

print(__name__)
if "__main__" == __name__:
    parser = argparse.ArgumentParser()
    parser.add_argument('--logging_level', default='DEBUG')
    parser.add_argument('--client_secrets', required=False, help="Path to client secrets")
    parser.add_argument('--datetime', default=datetime.now().strftime(date_format))
    parser.add_argument('--summary', required=True)
    parser.add_argument('--description', required=True)
    parser.add_argument('--url', required=True)
    parser.add_argument('--noauth_local_webserver', action='store_true',
                        default=True, help='Do not run a local web server.')
    args = parser.parse_args()
    main(args)
