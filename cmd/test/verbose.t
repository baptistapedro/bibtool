#!/bin/perl -W
# =============================================================================
#  
#  This file is part of BibTool.
#  It is distributed under the GNU General Public License.
#  See the file COPYING for details.
#  
#  (c) 2015 Gerd Neugebauer
#  
#  Net: gene@gerd-neugebauer.de
#  
#*=============================================================================

=head1 NAME

verbose.t - Test suite for the BibTool built-in verbose.

=head1 SYNOPSIS

verbose.t

=head1 DESCRIPTION

This module contains some test cases. Running this module as program
will run all test cases and print a summary for each. Optionally files
*.out and *.err are left if the expected result does not match the
actual result.

=head1 OPTIONS

none

=head1 AUTHOR

Gerd Neugebauer

=cut

use strict;
use BUnit;

#------------------------------------------------------------------------------
BUnit::run(name         => 'verbose-0',
	   resource => <<__EOF__ ,
-verbose;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(- verbose)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'verbose-1',
	   resource => <<__EOF__ ,
verbose = true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(verbose true)
__EOF__

#------------------------------------------------------------------------------
BUnit::run(name         => 'verbose-2',
	   resource => <<__EOF__ ,
verbose true;
__EOF__
	   expected_err => '',
	   expected_out => <<__EOF__ );
(verbose true)
__EOF__

1;
#------------------------------------------------------------------------------
# Local Variables: 
# mode: perl
# End: 