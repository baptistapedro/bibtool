/*** cstring.c*****************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 2016 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/symbols.h>
#include <bibtool/error.h>
#include <bibtool/type.h>
#include <bibtool/sbuffer.h>
#include "binding.h"
#include "lcore.h"

/*****************************************************************************/
/* Internal Programs                                                         */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif

/*****************************************************************************/
/* External Programs                                                         */
/*===========================================================================*/


/*---------------------------------------------------------------------------*/


Binding cs_binding = NULL;		   	   /*                        */

#define Bind(NAME,GET)  bind(cs_binding, symdef(symbol((String)NAME),     \
						0, 0, GET, NULL));

/*-----------------------------------------------------------------------------
** Function:	m_length()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_length(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{						   /*                        */
  no_args(args, "length");	   	   	   /*                        */
  return NumberTerm(strlen((char*)TString(string)));/*                       */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_trim()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_trim(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ String s = TString(string);			   /*                        */
  StringBuffer *sb;			   	   /*                        */
  char *cp, *str;				   /*                        */
  Term t;					   /*                        */
  no_args(args, "trim");	   	   	   /*                        */
 						   /*                        */
  sb = sbopen();				   /*                        */
  sbputs((char*)s, sb);				   /*                        */
  str = sbflush(sb);				   /*                        */
  while (is_space(*str)) str++;			   /*                        */
  cp = str;					   /*                        */
  while (*cp) cp++;				   /*                        */
  for (cp--; cp	>= str && is_space(*cp) ;cp--)	   /*                        */
    *cp = '\0';					   /*                        */
 						   /*                        */
  t = StringTerm((String)str);			   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_concat()
** Type:	static Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_concat(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ Term t;					   /*                        */
  StringBuffer *sb = sbopen();			   /*                        */
  						   /*                        */
  sbputs((char*)TString(string), sb);		   /*                        */
 						   /*                        */
  for ( ; args; args = Cdr(args))		   /*                        */
  { t = eval_str(binding, Car(args));		   /*                        */
    sbputs((char*)TString(t), sb);		   /*                        */
    UnlinkTerm(t);				   /*                        */
  }						   /*                        */
 						   /*                        */
  t = StringTerm((String)sbflush(sb));		   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	m_substring()
** Type:	Term
** Purpose:	
**		
** Arguments:
**	binding	the binding
**	string	the string term
**	args	the arguments
** Returns:	
**___________________________________________________			     */
static Term m_substring(binding, string, args)	   /*                        */
  Binding binding;				   /*                        */
  Term string;					   /*                        */
  Term args;					   /*                        */
{ int start, len;				   /*                        */
  StringBuffer *sb;			   	   /*                        */
  char *cp;				   	   /*                        */
  Term t;					   /*                        */
 						   /*                        */
  start = num_arg(binding, &args, "substring");	   /*                        */
    						   /*                        */
  sb = sbopen();				   /*                        */
  for (cp = (char*)TString(string);		   /*                        */
       *cp && start-- > 0;			   /*                        */
       cp++);  					   /*                        */
 						   /*                        */
  if (args)				   	   /*                        */
  { len = num_arg(binding, &args, "substring");	   /*                        */
    no_args(args, "substring");			   /*                        */
 						   /*                        */
    for (; *cp && len-- > 0 ; cp++)		   /*                        */
    { sbputchar(*cp, sb); }			   /*                        */
  }						   /*                        */
  else						   /*                        */
  { for (; *cp; cp++)				   /*                        */
    { sbputchar(*cp, sb); }			   /*                        */
  }						   /*                        */
 						   /*                        */
  t = StringTerm((String)sbflush(sb));		   /*                        */
  sbclose(sb);					   /*                        */
  return t;	   	   		   	   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	class_string()
** Type:	void
** Purpose:	
**		
** Arguments:	none
** Returns:	nothing
**___________________________________________________			     */
void class_string()				   /*                        */
{						   /*                        */
  cs_binding = binding(127, NULL);		   /*                        */
 						   /*                        */
  Bind("as.boolean", m_as_boolean);		   /*                        */
  Bind("as.string", m_as_string);		   /*                        */
  Bind("as.number", m_as_number);		   /*                        */
  Bind("concat", m_concat);			   /*                        */
  Bind("length", m_length);			   /*                        */
  Bind("substring", m_substring);		   /*                        */
  Bind("trim", m_trim);		   		   /*                        */
}						   /*------------------------*/

/*---------------------------------------------------------------------------*/