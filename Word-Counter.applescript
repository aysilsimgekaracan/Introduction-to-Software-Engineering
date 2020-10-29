on run {input, parameters}
	
	-------------------------------------------------
	# Full path of selected items in Finder.
	-------------------------------------------------
	tell application "Finder"
		set finderSelList to selection as alias list
	end tell
	
	if finderSelList ≠ {} then
		repeat with i in finderSelList
			set contents of i to POSIX path of (contents of i)
		end repeat
		
		set AppleScript's text item delimiters to linefeed
		finderSelList as text
	end if
	-------------------------------------------------
	
	tell application "Terminal"
		
		do script ""
		
		activate
		
		do script "g++ -std=c++11 -o Word_Counter/a.out Word_Counter/word_counter.cpp" in front window
		
		delay 1
		
		do script "Word_Counter/a.out" in front window
		
		delay 2
		
		do script finderSelList in front window
		
		delay 1
		
	end tell
	
	
	return input
end run

