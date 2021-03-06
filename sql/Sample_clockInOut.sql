DROP TABLE IF EXISTS ClockInOut;

-- Time data for first invoice
INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-06 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 19:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    1,
    3
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-06 06:32:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 12:28:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 12:59:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-06 17:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    1,
    1
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-07 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 17:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    1,
    3
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-07 06:32:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 12:28:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 12:59:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-07 18:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    1,
    1
);

-- Time data for second invoice
INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-20 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 18:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    2,
    4
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-20 08:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 12:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 13:15:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 16:15:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    2,
    3
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-20 06:32:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 12:28:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 12:59:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-20 17:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    2,
    1
);

-- Time data for invoice 3
INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2015-01-06 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2015-01-06 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2015-01-06 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2015-01-06 17:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    3,
    2
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2016-01-06 06:32:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2016-01-06 12:28:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2016-01-06 12:59:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2016-01-06 16:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    3,
    5
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2017-01-07 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 18:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    3,
    2
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2017-01-07 06:32:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 12:28:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 12:59:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2017-01-07 17:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    3,
    5
);

-- Time data for invoice 4
INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-01 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-01 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-01 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-01 17:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    4,
    6
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-02 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-02 12:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-02 13:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-02 15:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    4,
    6
);

-- Time data for invoice 5
INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-03 06:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-03 11:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-03 12:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-03 18:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    5,
    1
);

INSERT INTO ClockInOut(clockIn, startLunch, endLunch, clockOut, job, eid)
  VALUES(
    TO_TIMESTAMP('2014-01-09 09:58:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-09 13:31:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-09 14:01:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    TO_TIMESTAMP('2014-01-09 14:02:00.742000000', 'YYYY-MM-DD HH24:MI:SS.FF'),
    5,
    1
);
