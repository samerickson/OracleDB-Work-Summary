DROP TABLE IF EXISTS Invoices;

INSERT INTO Invoices(po, client, status, issued, workStart, workEnd, description)
  VALUES (1, 1, 'completed',
    to_date('Jan 01, 2020', 'Mon dd, yyyy'),
    to_date('Jan 06, 2020', 'Mon dd, yyyy'),
    to_date('Jan 07, 2020', 'Mon dd, yyyy'),
    'Installed Point of Connection');

INSERT INTO Invoices(po, client, status, issued, workStart, workEnd, description)
  VALUES (2, 1, 'active',
    to_date('Jan 15, 2020', 'Mon dd, yyyy'),
    to_date('Jan 20, 2020', 'Mon dd, yyyy'),
    null,
    'Installed 4 zone irrigation system');

INSERT INTO Invoices(po, client, status, issued, workStart, workEnd, description)
  VALUES (3, 2, 'sent',
    to_date('Jan 1, 2020', 'Mon dd, yyyy'),
    to_date('Jan 03, 2020', 'Mon dd, yyyy'),
    to_date('Jan 07, 2020', 'Mon dd, yyyy'),
    'Fixed linebreak');

INSERT INTO Invoices(po, client, status, issued, workStart, workEnd, description)
  VALUES (4, 3, 'scheduled',
    to_date('Jan 08, 2020', 'Mon dd, yyyy'),
    null,
    null,
    'Installed new controller');

INSERT INTO Invoices(po, client, status, issued, workStart, workEnd, description)
  VALUES (5, 5, 'active',
    to_date('Jan 07, 2020', 'Mon dd, yyyy'),
    to_date('Jan 07, 2020', 'Mon dd, yyyy'),
    to_date('Jan 07, 2020', 'Mon dd, yyyy'),
    'Added new zone');
