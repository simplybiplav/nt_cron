# nt_cron

- Ignores lines which have invalid format
- Exits if config file "nt_cron.conf" is not able to open
- Default config file "/etc/nt_cron.conf" is not able to open
  
##  config format

[1] [2] [3] [4] [5] [6]
- [1] -> minutes ( 0-59)
- [2] -> Hours (0-23)
- [3] -> Days of Month (1-31)
- [4] -> Month (1-12)
- [5] -> Days of Week ( 0-6 )
- [6] -> command

###  accepted format for 1-5

  -  `*`
  -  0,1,2,3,4
  -  */5
  -  4-8/7
  -  0,2-4,7-9

### eg:

`* * * * *  command1 arg1 arg 2`

`*/5 * * * *    command2 arg1`

`0-6,20,50 * * 2-4 * command3 arg4`



## TO-DO

- [ ] Take argument
  - [x] custom config file path
  - [x] run as foreground
  - [ ] any others ?
- [x] Run as daemon 
- [ ] Signal handling SIGINT and others ?
- [ ] Optimize the algorithm for time matching
- [ ] Code documentation in doxygen format 

  
