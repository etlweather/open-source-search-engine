import pytest


@pytest.mark.parametrize('query, fx_qlang, fx_blang, fx_fetld, fx_country, expected_lang', [
    # query         qlang       blang       fetld       country     expected
    ('øl',          '',         '',         '',         '',         'en'),  # wrong
    ('øl',          'da',       '',         '',         '',         'da'),
    ('øl',          'da',       'en-US',    '',         '',         'da'),
    ('øl',          'en',       'da-DK',    'findx.dk', 'dk',       'en'),  # make sure only fx_qlang is used when set
    ('øl',          '',         'en-US',    'findx.dk', '',         'en'),  # wrong
    ('øl',          '',         'en-US',    '',         'dk',       'en'),  # wrong
    ('Smølferne',   '',         '',         '',         '',         'da'),
    ('Smølferne',   '',         'en-US',    '',         '',         'da'),
    ('Smølferne',   '',         '',         '',         'uk',       'da'),
    ('Smølferne',   '',         'en-US',    '',         'uk',       'da'),
    ('The Smurfs',  'en',       '',         '',         '',         'en'),
    ('The Smurfs',  'en',       'da-DK',    '',         '',         'en'),
    ('The Smurfs',  '',         'da-DK',    '',         '',         'en'),
    ('The Smurfs',  '',         '',         '',         'dk',       'en'),
    ('The Smurfs',  '',         'da-DK',    '',         'dk',       'da'),  # wrong
    ('Smurfene',    '',         '',         '',         '',         'is'),  # wrong
    ('Smurfene',    '',         'en-US',    '',         '',         'en'),  # wrong
    ('Smurfene',    '',         'no-NO',    '',         '',         'no'),
    ('Smurfene',    '',         '',         '',         'no',       'no'),
    ('kanin',       '',         '',         '',         '',         'tl'),  # wrong
    ('kanin',       '',         'da-dk',    '',         '',         'da'),
    ('kanin',       'da',       '',         '',         '',         'da'),
    ('kanin',       '',         '',         '',         'dk',       'tl'),  # wrong
])
def test_search_language_hint(gb_api, query, fx_qlang, fx_blang, fx_fetld, fx_country, expected_lang):
    payload = {}

    # add language hints
    payload.update({'fx_qlang': fx_qlang})
    payload.update({'fx_blang': fx_blang})
    payload.update({'fx_fetld': fx_fetld})
    payload.update({'fx_country': fx_country})

    result = gb_api.search(query, payload)

    assert result['queryInfo']['queryLanguageAbbr'] == expected_lang
