L7:
if a > b goto L0
goto L1
L0:
b = c
L6:
if c > b goto L2
goto L3
L2:
a = b
if a > b goto L4
goto L5
L4:
goto L6
L5:
b = c
goto L3
goto L6
L3:
a = c
goto L7
c = b
goto L7
L1:
