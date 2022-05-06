BEGIN { RS="" ; FS = "\n" }
{ count++ }
END { print count }

