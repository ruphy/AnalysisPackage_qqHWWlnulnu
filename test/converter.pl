#!/usr/local/bin/perl

print $ARGV[0]."\n" ;
open(NUMS, $ARGV[0]);
@lines = <NUMS>;
close(NUMS);			   # Close the file
$cutsnum = (@lines - 1)/2 ;
print @lines." ".$cutsnum."\n" ;


# read the first line
@samples = <$lines[0]> ;
$size = @samples ;
print "number of samples: ".$size ;
print "--- --- --- --- --- --- --- \n" ;
print @samples[0] ;
for ($j = 1; $j < $size; ++$j)
  {
    print " & ".$samples[$j] ;
  }
print " & tot \\\\\n" ;

# read the numbers
for ($i = 0; $i < $cutsnum; ++$i)
  {
    @eventstemp = <$lines[$i+1]> ;    
    @errtemp = <$lines[$i+1+$cutsnum]> ;

    $size = @eventstemp ;
    $total = 0 ;
    $totalErr = 0 ;
#     print @events[0]." \$\\pm\$ ".(($err[$j]-1)*$total) ;
    for ($j = 0; $j < $size; ++$j)
      {
        $events  = sprintf("%.3f", $eventstemp[$j]);
        if ($errtemp[$j] != -1) { 
         $err     = sprintf("%.3f", (($errtemp[$j]-1.)*$eventstemp[$j])) ;
        }
        else {
         $err     = sprintf("%.3f", -1) ;
        }
        
        if ($j!=0) {
           print " & " ;
        }

        if ($j != ($size-1)) { #check if DATA
         print "  ".$events." \$\\pm\$ ".$err ;
         $total = $total + $events ;
         if ($errtemp[$j] != -1) { 
          $totalErr = $totalErr + (($errtemp[$j]-1.)*$eventstemp[$j]) ;
         }
         else {
          #
         }
       }
       else { # data 
        print "  ".$events." " ;
       }

      }
    print " & ".$total." \$\\pm\$ ".$totalErr." \\\\\n" ;
  }