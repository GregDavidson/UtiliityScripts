#!/bin/bash
# OBSOLETE???
# see [[file:~/SW/Emacs/bin/make-org-links]]

shopt -s nullglob								# <---
# shopt -s extglob								# <---
# would allow, e.g. ${x%%+(/)} to strip ALL trailing slashes

links_name="ORG-LINKS.org"
root_names=(  README.org index.org INDEX.org )
this_pgm="${0##*/}"
usage="$this_pgm [ DIR[/$links_name] ]"
purpose='Index org files beneath a given directory'

ignore() {
		local d="${1%/}"
		case "${d##*/}" in
				[Ll]imbo) return 0 ;;
				[Ff]oo) return 0 ;;
				[Tt]mp) return 0 ;;
				*~) return 0 ;;
		esac
		return 1
}

if [ $# -eq 0 ] ; then
	if [ -d "$HOME/$USER" ]
	then dir="$HOME/$USER"
	else dir="$HOME"
	fi
elif [ -d "$1" ] ; then	dir="$1"
elif [ X"$links_name" != X"${1%%*/}1" ]; then
	>&2 echo "$usage" ; exit 1
else
		dir="${1#/*}"
		if ! [ -d "$dir" ]; then
			>&2 echo "$usage" ; exit 2
		fi
fi

# print_section stars title
# suppress newline when 1 star??
print_section() {
	printf '\n%s %s\n\n' "$1" "$2"
}

cd "$dir"
exec >"$links_name"
print_section '*' "$dir links"
dir=''

# print_link  dir short_dir path [title]
# glob chars in $dir will cause trouble!! <---
print_link() {
	local dir="${1%/}" d="${2%/}" path="${3%d}" title="$4"
	if [ "X$dir" != "X$d" ] || [ -n "$title" ]; then
		printf -- '- [[%s][%s]]\n' "$path" "${title:-${d:+/}${path##*/}}"
	else
		printf -- '- [[%s]]\n' "$path"
	fi
}

# exists_some array-of-filenames [directory-path-with-trailing-slash]
# at least one of the files exists in current or specified directory
exists_some() {
		local dir="$2"
		local -n names="$1"						# array nameref
		local i=0 n="${#names[@]}"
		while (( i < n )) ; do
				[ -f "${dir}${names[i]}" ] && return 0
				let i++
		done
		return 1
}

# list_links dir short_dir stars
# dir = relative or absolute directory, ending in / if non-empty
# d = short_dir = path relative to most recent '*' "root" section
# a string of stars showing our section level
# assumes shopt -s nullglob <---
list_links() {
		set -o xtrace
		local dir="${1:+$1}" old_d="${2:+$2}" d old_stars="$3" stars f
		# if there's a links file in this subdirectory
		# this is a leaf in the currently open links file
		# run a new script instance to update this links file
		if [ -n "$dir" ] && [ -f "$dir$links_name" ]; then
			print_link "$dir" "$d" "$dir$links_name"
			"$0" "$dir" 				# run in backgound??
			return								# <---
		fi
		if [ -n "$dir" ] && exists_some root_names "$dir"; then
			d=''
			stars="*$old_stars"
			print_section "$stars" "$dir"
		else
			d="$old_d"
			stars="$old_stars"
		fi
		for f in ${dir}*.org; do
				[ -z "$dir" -a X"$f" == X"$dir$links_name" ] || print_link "$dir" "$d" "$f"
		done
		for f in ${dir}*/; do
				! ignore "$f" &&
					list_links "${f}" "$d${f##*/}/" "$stars" # recurse!
		done
}

list_links '' '' '*'
