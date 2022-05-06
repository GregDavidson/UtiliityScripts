#!/bin/bash

## emacs-launcher-common.bash
# Copyright (c) 2014 J. Greg Davidson

# This script is designed to be sourced by my
# scripts which launch emacs and emacsclient
# with my favorite options.  Because the options
# supported by emacs and emacsclient are quite
# incompatible and inconsistent I've created this
# fancy general machinery here.  It could be
# further generalized for other programs.

# For simplicity, I'm only supporting Gnu-style
# long options.

# If you don't have my jgd emacs extensions
# be sure and set [jgd]=false below!!

# You might also want to change fav_font()

## Errors, Warnings, Standard Error Stream

pgm_name="${0##*/}"
err_out() {	>&2 printf "%s\n" "$*"; } # to standard error
err_level() {
	local level="$1" ; shift
	err_out "$pgm_name $level: $*"
}
warning() { err_level warning "$*"; }
error() {
 local code="$1"; shift
 err_level error "$*"; exit "$code"
}

type "$launch" >/dev/null 2>&1 ||
	error 2 "Expected launch command $launch!"

[[ -v option_arity ]] && (( ${#option_arity[@]} ))  ||
	warning "No option_arity array = no option checking!"

## Launcher Modes
	 
# modes are meta options, i.e. options for
# the launcher, not for the program we're
# launching!
declare -A mode=(
	[exec]=true									# exec the program to launch
	[gui-bg]=false									# if GUI then BackGround
	[show]=true										# show the command first
	[test]=false									# do not run the command
	[jgd]=true										# add jgd emacs extras
)

set_mode() {
	case "$1" in
		-exec) mode[exec]=true mode[gui-bg]=false ;;
		-gui-bg) mode[gui-bg]=true mode[exec]=false ;;
		-show) mode[show]=true ;;
		-quiet) mode[show]=false ;;
		-test) mode[test]=true ;;
		-jgd) mode[jgd]=true ;;
		-standard)  mode[jgd]=false ;;
		*) error 3 "option $1 unknown -- use long option!" ;;
	esac
}

## Options

declare -a options=()						# accumulates options
declare -A options_keys=()			# records key indices
declare -A options_vals=()			# records option indices
declare -a args=()							# accumulates arguments
declare -A args_vals=()					# records arg indices

# check option validity AFTER parsing
check_option() {
	local n="${option_arity[the_key]}"
	[[ -z "$n" ]] && return 0				# no check possible!
	case "$the_option" in
		*=*) (( n == 2 )) ||
					 error 5 "Unexpected option value in $*" ;;
		*) (( n == 1 )) ||
				 error 6 "Missing option value in $*" ;;
	esac
	return 0
}

# encode_option key [val]
# sets the_{key,val,option}
encode_option() {
	the_key="$1" the_val="$2"
	case $# in
		1) the_option="--${1}" ;;
		2) the_option="--${1}=${2}" ;;
		*) error 7 "get_option $@" ;;
	esac
}

# encode_option --key[=val]
# sets the_{key,val,option}
decode_option() {
	(( $# == 1 )) || error 8 "get_option $@"
	the_option="$1"
	local opt="${1#--}"
	case "$opt" in
		*=*) the_key="${opt%%=*}" the_val="${opt#*=}" ;;
		*) the_key="${opt}" the_val='' ;;
	esac
}

# get_option --key[=val] | key [val]
# sets the_{key,val,option}
# succeeds iff already have such option
get_option() {
	local opt							# long option w/o leading --
	case "$1" in
		---*) error 9 get_option "$@" ;;
		--*) decode_option "$@" ;;
		-*) error 10 get_option "$@" ;;
		*) encode_option "$@" ;;
	esac
	check_option
	# return whether we already have this option
	[[ -n "${options_vals[$the_option]}" ]]
}

# add_option key [val]
# adds long option if not already present
add_option() {
	get_option "$@" && return 1
	local n="${#options[@]}"
	options[${#options[@]}]="$the_option"
	options_keys[$the_key]+="${options_keys[$the_key]:+ }$n"
	options_vals[$the_option]+="${options_vals[$the_option]:+ }$n"
}

# replace_option --key=val | key val
# adds option or updates option to this value
# there should be either 0 or 1 options with this key!!
replace_option() {
	get_option "$@" && return 1
	local -a indices=( ${options_keys[$the_key]} )
	case ${#indices[@]} in
		0) add_option "$@" ;;
		1) local key_index=${indices[0]}
			 local old_option="${options[$key_index]}"
			 unset options_vals["$old_option"]
			 options[$key_index]="$the_option"
			 options_keys[$the_key]=$key_index
			 options_vals[$the_option]=$key_index ;;
		*) error 11 "replace_option $@; options=${options[@]}" ;;
	esac
}

# Args

add_arg() {
	for a; do
		[[ -n "${args_vals[$a]}" ]] && continue # already have it!
		local n="${#args[@]}"
		args[$n]="$a"
		args_vals[$a]="$n"
	done
}

# define launch-specific add_eval function
eval "$to_add_eval"

# turn a list into a parenthesized s-expression
# turning any : prefixes into single quotes
list_of() {
	printf "%s\n" "($*)" | sed "s/\\B:/'/g"
	#	sed -e 's/[\\"$]/\\&/g' -e "s/\\B:/'/g" -e "s/.*/\"(&)\"/"
}

# Protection against inconsistent height/width constraints

height_specified=''							# current height constraint
width_specified=''							# current width constraint

## Constraints

# specify height/width constraint
specify() {
	(( $# == 2 )) || error 13 wrong arity $# in "specify $*"
	case "$1" in
		height)
			[[ -n "$height_specified" ]] && {
				warning "specify $* conflicts with earlier $1  $2"
				return 1
			}
			height_specified="$2"
			;;
		width)
			[[ -n "$width_specified" ]] && {
				warning "specify $* conflicts with earlier $1  $2"
				return 1
			}
			width_specified="$2"
			;;
		both) specify height "$2" ; specify width "$2" ;; 
	esac
	return 0
}

## Geometry

ok_geometry() {
	[[ -n "$1" ]] &&
	[[ "$1" =~ (([0-9]+)x([0-9]+))?([+-][0-9]+[+-]([0-9]+))? ]]
}

parse_geometry() {
	echo "$1" | sed \
		-e '/^\([0-9]\+\)x\([0-9]\+\)/s//width=\1;height=\2;/' \
		-e '/\([+-][0-9]\+\)/s//left=\1;/' \
		-e '/;\([+-][0-9]\+\)/s//;right=\1;/' \
		-e 's/+//g'
}

get_geometry() {
	ok_geometry "$1" || {
		warning bad geometry "$1"
		return 1
	}
	eval $(parse_geometry "$1")
	[[ -n "$width" ]] && specify width width || return 1
	[[ -n "$height" ]]  && specify height height || return 1
	[[ -n "$left" ]] && specify width left || return 1
	[[ -n "$top" ]] && specify height top || return 1
	return 0
}

## XDPYINFO

have_gui() { [[ -n "$DISPLAY" ]]; }

parse_xdpyinfo() {	xdpyinfo | sed -n \
'/^ *\(resolution\|dimensions\): *\([1-9][0-9]*\)x.*/s//\1=\2/p'
}

get_xdpyinfo() {
	have_gui || return 1
	eval $(parse_xdpyinfo)
	return 0
}

set_font_size() {
	if [[ "$resolution" -gt 100 ]]; then font_size=12
	elif [[ "$resolution" -gt 92 ]]; then font_size=10
 	else font_size=9
	fi
}

# fav_font [font-size]
fav_font() {
	printf 'DejaVu Sans condensed-%d' "${1:-14}"
	# would any of these also work:?
	#	printf 	"Dejavu Sans Condensed-%s" "${1:-14}" 
	#	printf 	"Dejavu Sans-$s:widthtype=condensed" ""${1:-14}" "
	# Note: (frame-parameter nil 'font) -->
	# "-unknown-DejaVu Sans-normal-normal-semicondensed-*-13-*-*-*-*-0-iso10646-1"
}

# let's hope I soon need to handle qhd! :)
set_num_cols() {
	if [[ "$dimensions" -gt 1900 && "$resolution" -gt 100 ]];	then num_cols=3
	elif [[ "$dimensions" -gt 1900 && "$resolution" -gt 80 ]];  then num_cols=4
	else num_cols=1
	fi
}

get_xdpyinfo && {
	# choose nice default font_size and num_cols
	# based on horizontal resolution and dimensions:
	set_font_size
	set_num_cols
	"${mode[jgd]}" && {
		# pass this information into emacs or emacsclient
		add_eval defconst jgd-horizontal-resolution $resolution
		add_eval defconst jgd-screen-width $dimensions
		add_eval defconst jgd-num-cols $num_cols
	}
}

## launch_command

launch_command() {
	${mode[show]} && err_out "$launch" "${options[@]}" -- "${args[@]}"
	${mode[test]} && return 0
	${mode[exec]} && exec "$launch" "${options[@]}" -- "${args[@]}"
	"$launch" "${options[@]}" -- "${args[@]}"
}
