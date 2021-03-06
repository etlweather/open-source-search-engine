#!/bin/bash

if [ $# -ne 1 ]; then
	echo "`basename $0`: usage: <outputfile>" >&2
	exit 99
fi

langscodes=""
for f in query_stop_words.??.txt; do
	langcode=`echo $f|cut -d. -f2`
	langcodes="$langcodes $langcode"
done

echo "//auto-generated by $0" >$1

for langcode in $langcodes; do
	echo "#include \"query_stop_words.$langcode.inc"\" >>$1
done

cat - >>$1 <<EOF
static const struct {
	lang_t lang;
	const char * const *words;
} s_query_stop_words_lang[] = {
EOF

for langcode in $langcodes; do
	case $langcode in
		xx) lang=langUnknown ;;
		en) lang=langEnglish ;;
		fr) lang=langFrench ;;
		es) lang=langSpanish ;;
		ru) lang=langRussian ;;
		tr) lang=langTurkish ;;
		ja) lang=langJapanese ;;
		zh_tw) lang=langChineseTrad ;;
		zh_cn) lang=langChineseSimp ;;
		ko) lang=langKorean ;;
		de) lang=langGerman ;;
		nl) lang=langDutch ;;
		it) lang=langItalian ;;
		fi) lang=langFinnish ;;
		sv) lang=langSwedish ;;
		no) lang=langNorwegian ;;
		pt) lang=langPortuguese ;;
		vi) lang=langVietnamese ;;
		ar) lang=langArabic ;;
		he) lang=langHebrew ;;
		id) lang=langIndonesian ;;
		el) lang=langGreek ;;
		th) lang=langThai ;;
		hi) lang=langHindi ;;
		bn) lang=langBengala ;;
		pl) lang=langPolish ;;
		tl) lang=langTagalog ;;
		la) lang=langLatin ;;
		eo) lang=langEsperanto ;;
		ca) lang=langCatalan ;;
		bg) lang=langBulgarian ;;
		tx) lang=langTranslingual ;;
		sr) lang=langSerboCroatian ;;
		hu) lang=langHungarian ;;
		da) lang=langDanish ;;
		lt) lang=langLithuanian ;;
		cs) lang=langCzech ;;
		gl) lang=langGalician ;;
		ka) lang=langGeorgian ;;
		gd) lang=langScottishGaelic ;;
		go) lang=langGothic ;;
		ro) lang=langRomanian ;;
		ga) lang=langIrish ;;
		lv) lang=langLatvian ;;
		hy) lang=langArmenian ;;
		is) lang=langIcelandic ;;
		ag) lang=langAncientGreek ;;
		gv) lang=langManx ;;
		io) lang=langIdo ;;
		fa) lang=langPersian ;;
		te) lang=langTelugu ;;
		vv) lang=langVenetian ;;
		mg) lang=langMalgasy ;;
		ku) lang=langKurdish ;;
		lb) lang=langLuxembourgish ;;
		et) lang=langEstonian ;;
		mt) lang=langMaltese ;;
		sk) lang=langSlovak ;;
		sl) lang=langSlovenian ;;
		eu) lang=langBasque ;;
		cy) lang=langWelsh ;;
		kl) lang=langGreenlandic ;;
		fo) lang=langFaroese ;;
		*)
			ech o"Unknown language in $f" >&2
			exit 99
	esac
	echo "	{$lang,s_query_stop_words_$langcode}," >>$1
done

echo "};" >>$1
